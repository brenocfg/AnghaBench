#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  tm ;
struct tm {void* tm_sec; void* tm_min; void* tm_hour; void* tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;
struct TYPE_6__ {int abstract_file; int application_id; int biblio_file; int boot; int boot_catalog; int boot_load_seg; int boot_load_size; int compression_level; int copyright_file; char iso_level; int publisher; int volume_id; int /*<<< orphan*/  zisofs; void* rr; int /*<<< orphan*/  pad; int /*<<< orphan*/  limit_dirs; int /*<<< orphan*/  limit_depth; int /*<<< orphan*/  joliet; int /*<<< orphan*/  boot_type; int /*<<< orphan*/  boot_info_table; int /*<<< orphan*/  allow_vernum; } ;
struct TYPE_5__ {char compression_level; } ;
struct TYPE_4__ {void* boot_load_size; void* boot_load_seg; int /*<<< orphan*/  catalog_filename; int /*<<< orphan*/  boot_filename; } ;
struct iso9660 {TYPE_3__ opt; int /*<<< orphan*/  volume_identifier; int /*<<< orphan*/  publisher_identifier; int /*<<< orphan*/  birth_time; int /*<<< orphan*/  copyright_file_identifier; TYPE_2__ zisofs; TYPE_1__ el_torito; int /*<<< orphan*/  bibliographic_file_identifier; int /*<<< orphan*/  application_identifier; int /*<<< orphan*/  abstract_file_identifier; } ;
struct archive_write {int /*<<< orphan*/  archive; struct iso9660* format_data; } ;

/* Variables and functions */
 int ABSTRACT_FILE_SIZE ; 
 int APPLICATION_IDENTIFIER_SIZE ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int BIBLIO_FILE_SIZE ; 
 int COPYRIGHT_FILE_SIZE ; 
 int /*<<< orphan*/  OPT_BOOT_TYPE_FD ; 
 int /*<<< orphan*/  OPT_BOOT_TYPE_HARD_DISK ; 
 int /*<<< orphan*/  OPT_BOOT_TYPE_NO_EMU ; 
 int /*<<< orphan*/  OPT_JOLIET_DISABLE ; 
 int /*<<< orphan*/  OPT_JOLIET_ENABLE ; 
 int /*<<< orphan*/  OPT_JOLIET_LONGNAME ; 
 void* OPT_RR_DISABLED ; 
 void* OPT_RR_STRICT ; 
 void* OPT_RR_USEFUL ; 
 int /*<<< orphan*/  OPT_ZISOFS_DIRECT ; 
 int /*<<< orphan*/  OPT_ZISOFS_DISABLED ; 
 int PUBLISHER_IDENTIFIER_SIZE ; 
 int VOLUME_IDENTIFIER_SIZE ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  archive_strcpy (int /*<<< orphan*/ *,char const*) ; 
 int get_num_opt (struct archive_write*,int*,int,int,char const*,char const*) ; 
 int get_str_opt (struct archive_write*,int /*<<< orphan*/ *,int,char const*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mktime (struct tm*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 void* strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
iso9660_options(struct archive_write *a, const char *key, const char *value)
{
	struct iso9660 *iso9660 = a->format_data;
	const char *p;
	int r;

	switch (key[0]) {
	case 'a':
		if (strcmp(key, "abstract-file") == 0) {
			r = get_str_opt(a,
			    &(iso9660->abstract_file_identifier),
			    ABSTRACT_FILE_SIZE, key, value);
			iso9660->opt.abstract_file = r == ARCHIVE_OK;
			return (r);
		}
		if (strcmp(key, "application-id") == 0) {
			r = get_str_opt(a,
			    &(iso9660->application_identifier),
			    APPLICATION_IDENTIFIER_SIZE, key, value);
			iso9660->opt.application_id = r == ARCHIVE_OK;
			return (r);
		}
		if (strcmp(key, "allow-vernum") == 0) {
			iso9660->opt.allow_vernum = value != NULL;
			return (ARCHIVE_OK);
		}
		break;
	case 'b':
		if (strcmp(key, "biblio-file") == 0) {
			r = get_str_opt(a,
			    &(iso9660->bibliographic_file_identifier),
			    BIBLIO_FILE_SIZE, key, value);
			iso9660->opt.biblio_file = r == ARCHIVE_OK;
			return (r);
		}
		if (strcmp(key, "boot") == 0) {
			if (value == NULL)
				iso9660->opt.boot = 0;
			else {
				iso9660->opt.boot = 1;
				archive_strcpy(
				    &(iso9660->el_torito.boot_filename),
				    value);
			}
			return (ARCHIVE_OK);
		}
		if (strcmp(key, "boot-catalog") == 0) {
			r = get_str_opt(a,
			    &(iso9660->el_torito.catalog_filename),
			    1024, key, value);
			iso9660->opt.boot_catalog = r == ARCHIVE_OK;
			return (r);
		}
		if (strcmp(key, "boot-info-table") == 0) {
			iso9660->opt.boot_info_table = value != NULL;
			return (ARCHIVE_OK);
		}
		if (strcmp(key, "boot-load-seg") == 0) {
			uint32_t seg;

			iso9660->opt.boot_load_seg = 0;
			if (value == NULL)
				goto invalid_value;
			seg = 0;
			p = value;
			if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X'))
				p += 2;
			while (*p) {
				if (seg)
					seg <<= 4;
				if (*p >= 'A' && *p <= 'F')
					seg += *p - 'A' + 0x0a;
				else if (*p >= 'a' && *p <= 'f')
					seg += *p - 'a' + 0x0a;
				else if (*p >= '0' && *p <= '9')
					seg += *p - '0';
				else
					goto invalid_value;
				if (seg > 0xffff) {
					archive_set_error(&a->archive,
					    ARCHIVE_ERRNO_MISC,
					    "Invalid value(over 0xffff) for "
					    "option ``%s''", key);
					return (ARCHIVE_FATAL);
				}
				p++;
			}
			iso9660->el_torito.boot_load_seg = (uint16_t)seg;
			iso9660->opt.boot_load_seg = 1;
			return (ARCHIVE_OK);
		}
		if (strcmp(key, "boot-load-size") == 0) {
			int num = 0;
			r = get_num_opt(a, &num, 0xffff, 1, key, value);
			iso9660->opt.boot_load_size = r == ARCHIVE_OK;
			if (r != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			iso9660->el_torito.boot_load_size = (uint16_t)num;
			return (ARCHIVE_OK);
		}
		if (strcmp(key, "boot-type") == 0) {
			if (value == NULL)
				goto invalid_value;
			if (strcmp(value, "no-emulation") == 0)
				iso9660->opt.boot_type = OPT_BOOT_TYPE_NO_EMU;
			else if (strcmp(value, "fd") == 0)
				iso9660->opt.boot_type = OPT_BOOT_TYPE_FD;
			else if (strcmp(value, "hard-disk") == 0)
				iso9660->opt.boot_type = OPT_BOOT_TYPE_HARD_DISK;
			else
				goto invalid_value;
			return (ARCHIVE_OK);
		}
		break;
	case 'c':
		if (strcmp(key, "compression-level") == 0) {
#ifdef HAVE_ZLIB_H
			if (value == NULL ||
			    !(value[0] >= '0' && value[0] <= '9') ||
			    value[1] != '\0')
				goto invalid_value;
                	iso9660->zisofs.compression_level = value[0] - '0';
			iso9660->opt.compression_level = 1;
                	return (ARCHIVE_OK);
#else
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "Option ``%s'' "
			    "is not supported on this platform.", key);
			return (ARCHIVE_FATAL);
#endif
		}
		if (strcmp(key, "copyright-file") == 0) {
			r = get_str_opt(a,
			    &(iso9660->copyright_file_identifier),
			    COPYRIGHT_FILE_SIZE, key, value);
			iso9660->opt.copyright_file = r == ARCHIVE_OK;
			return (r);
		}
#ifdef DEBUG
		/* Specifies Volume creation date and time;
		 * year(4),month(2),day(2),hour(2),minute(2),second(2).
		 * e.g. "20090929033757"
		 */
		if (strcmp(key, "creation") == 0) {
			struct tm tm;
			char buf[5];

			p = value;
			if (p == NULL || strlen(p) < 14)
				goto invalid_value;
			memset(&tm, 0, sizeof(tm));
			memcpy(buf, p, 4); buf[4] = '\0'; p += 4;
			tm.tm_year = strtol(buf, NULL, 10) - 1900;
			memcpy(buf, p, 2); buf[2] = '\0'; p += 2;
			tm.tm_mon = strtol(buf, NULL, 10) - 1;
			memcpy(buf, p, 2); buf[2] = '\0'; p += 2;
			tm.tm_mday = strtol(buf, NULL, 10);
			memcpy(buf, p, 2); buf[2] = '\0'; p += 2;
			tm.tm_hour = strtol(buf, NULL, 10);
			memcpy(buf, p, 2); buf[2] = '\0'; p += 2;
			tm.tm_min = strtol(buf, NULL, 10);
			memcpy(buf, p, 2); buf[2] = '\0';
			tm.tm_sec = strtol(buf, NULL, 10);
			iso9660->birth_time = mktime(&tm);
			return (ARCHIVE_OK);
		}
#endif
		break;
	case 'i':
		if (strcmp(key, "iso-level") == 0) {
			if (value != NULL && value[1] == '\0' &&
			    (value[0] >= '1' && value[0] <= '4')) {
				iso9660->opt.iso_level = value[0]-'0';
				return (ARCHIVE_OK);
			}
			goto invalid_value;
		}
		break;
	case 'j':
		if (strcmp(key, "joliet") == 0) {
			if (value == NULL)
				iso9660->opt.joliet = OPT_JOLIET_DISABLE;
			else if (strcmp(value, "1") == 0)
				iso9660->opt.joliet = OPT_JOLIET_ENABLE;
			else if (strcmp(value, "long") == 0)
				iso9660->opt.joliet = OPT_JOLIET_LONGNAME;
			else
				goto invalid_value;
			return (ARCHIVE_OK);
		}
		break;
	case 'l':
		if (strcmp(key, "limit-depth") == 0) {
			iso9660->opt.limit_depth = value != NULL;
			return (ARCHIVE_OK);
		}
		if (strcmp(key, "limit-dirs") == 0) {
			iso9660->opt.limit_dirs = value != NULL;
			return (ARCHIVE_OK);
		}
		break;
	case 'p':
		if (strcmp(key, "pad") == 0) {
			iso9660->opt.pad = value != NULL;
			return (ARCHIVE_OK);
		}
		if (strcmp(key, "publisher") == 0) {
			r = get_str_opt(a,
			    &(iso9660->publisher_identifier),
			    PUBLISHER_IDENTIFIER_SIZE, key, value);
			iso9660->opt.publisher = r == ARCHIVE_OK;
			return (r);
		}
		break;
	case 'r':
		if (strcmp(key, "rockridge") == 0 ||
		    strcmp(key, "Rockridge") == 0) {
			if (value == NULL)
				iso9660->opt.rr = OPT_RR_DISABLED;
			else if (strcmp(value, "1") == 0)
				iso9660->opt.rr = OPT_RR_USEFUL;
			else if (strcmp(value, "strict") == 0)
				iso9660->opt.rr = OPT_RR_STRICT;
			else if (strcmp(value, "useful") == 0)
				iso9660->opt.rr = OPT_RR_USEFUL;
			else
				goto invalid_value;
			return (ARCHIVE_OK);
		}
		break;
	case 'v':
		if (strcmp(key, "volume-id") == 0) {
			r = get_str_opt(a, &(iso9660->volume_identifier),
			    VOLUME_IDENTIFIER_SIZE, key, value);
			iso9660->opt.volume_id = r == ARCHIVE_OK;
			return (r);
		}
		break;
	case 'z':
		if (strcmp(key, "zisofs") == 0) {
			if (value == NULL)
				iso9660->opt.zisofs = OPT_ZISOFS_DISABLED;
			else {
#ifdef HAVE_ZLIB_H
				iso9660->opt.zisofs = OPT_ZISOFS_DIRECT;
#else
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "``zisofs'' "
				    "is not supported on this platform.");
				return (ARCHIVE_FATAL);
#endif
			}
			return (ARCHIVE_OK);
		}
		break;
	}

	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);

invalid_value:
	archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
	    "Invalid value for option ``%s''", key);
	return (ARCHIVE_FAILED);
}