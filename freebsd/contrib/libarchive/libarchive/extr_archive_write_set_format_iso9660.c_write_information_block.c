#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ abstract_file; scalar_t__ application_id; scalar_t__ allow_vernum; scalar_t__ biblio_file; scalar_t__ boot; scalar_t__ boot_catalog; scalar_t__ boot_info_table; scalar_t__ boot_load_seg; scalar_t__ boot_load_size; scalar_t__ boot_type; scalar_t__ compression_level; scalar_t__ copyright_file; char* iso_level; char* joliet; char* limit_depth; char* limit_dirs; char* pad; scalar_t__ publisher; char* rr; scalar_t__ volume_id; char* zisofs; } ;
struct TYPE_17__ {char* s; } ;
struct TYPE_16__ {char* s; } ;
struct TYPE_15__ {char* s; } ;
struct TYPE_14__ {char* compression_level; } ;
struct TYPE_22__ {char* s; } ;
struct TYPE_21__ {char* s; } ;
struct TYPE_12__ {char* boot_load_seg; char* boot_load_size; TYPE_9__ catalog_filename; TYPE_8__ boot_filename; } ;
struct TYPE_20__ {char* s; } ;
struct TYPE_19__ {char* s; } ;
struct TYPE_18__ {char* s; } ;
struct iso9660 {TYPE_11__ opt; TYPE_4__ volume_identifier; TYPE_3__ publisher_identifier; TYPE_2__ copyright_file_identifier; TYPE_1__ zisofs; TYPE_10__ el_torito; TYPE_7__ bibliographic_file_identifier; TYPE_6__ application_identifier; TYPE_5__ abstract_file_identifier; int /*<<< orphan*/  birth_time; } ;
struct archive_write {int /*<<< orphan*/  archive; scalar_t__ format_data; } ;
struct archive_string {int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __time64_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  KEY_FLG ; 
 int /*<<< orphan*/  KEY_HEX ; 
 int /*<<< orphan*/  KEY_INT ; 
 int /*<<< orphan*/  KEY_STR ; 
 size_t LOGICAL_BLOCK_SIZE ; 
 size_t NON_ISO_FILE_SYSTEM_INFORMATION_BLOCK ; 
 scalar_t__ OPT_ABSTRACT_FILE_DEFAULT ; 
 scalar_t__ OPT_ALLOW_VERNUM_DEFAULT ; 
 scalar_t__ OPT_APPLICATION_ID_DEFAULT ; 
 scalar_t__ OPT_BIBLIO_FILE_DEFAULT ; 
 scalar_t__ OPT_BOOT_CATALOG_DEFAULT ; 
 scalar_t__ OPT_BOOT_DEFAULT ; 
 scalar_t__ OPT_BOOT_INFO_TABLE_DEFAULT ; 
 scalar_t__ OPT_BOOT_LOAD_SEG_DEFAULT ; 
 scalar_t__ OPT_BOOT_LOAD_SIZE_DEFAULT ; 
 scalar_t__ OPT_BOOT_TYPE_DEFAULT ; 
 scalar_t__ OPT_BOOT_TYPE_FD ; 
 scalar_t__ OPT_BOOT_TYPE_HARD_DISK ; 
 scalar_t__ OPT_COMPRESSION_LEVEL_DEFAULT ; 
 scalar_t__ OPT_COPYRIGHT_FILE_DEFAULT ; 
 char* OPT_ISO_LEVEL_DEFAULT ; 
 char* OPT_JOLIET_DEFAULT ; 
 char* OPT_JOLIET_LONGNAME ; 
 char* OPT_LIMIT_DEPTH_DEFAULT ; 
 char* OPT_LIMIT_DIRS_DEFAULT ; 
 char* OPT_PAD_DEFAULT ; 
 scalar_t__ OPT_PUBLISHER_DEFAULT ; 
 char* OPT_RR_DEFAULT ; 
 char* OPT_RR_DISABLED ; 
 char* OPT_RR_STRICT ; 
 char* OPT_RR_USEFUL ; 
 scalar_t__ OPT_VOLUME_ID_DEFAULT ; 
 char* OPT_ZISOFS_DEFAULT ; 
 int /*<<< orphan*/  _ctime64_s (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * archive_string_ensure (struct archive_string*,size_t) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_sprintf (struct archive_string*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_version_string () ; 
 int /*<<< orphan*/  ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctime_r (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_option_info (struct archive_string*,int*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wb_buffptr (struct archive_write*) ; 
 int wb_consume (struct archive_write*,size_t) ; 
 size_t wb_remaining (struct archive_write*) ; 
 int wb_write_out (struct archive_write*) ; 

__attribute__((used)) static int
write_information_block(struct archive_write *a)
{
	struct iso9660 *iso9660;
	char buf[128];
	const char *v;
	int opt, r;
	struct archive_string info;
	size_t info_size = LOGICAL_BLOCK_SIZE *
			       NON_ISO_FILE_SYSTEM_INFORMATION_BLOCK;

	iso9660 = (struct iso9660 *)a->format_data;
	if (info_size > wb_remaining(a)) {
		r = wb_write_out(a);
		if (r != ARCHIVE_OK)
			return (r);
	}
	archive_string_init(&info);
	if (archive_string_ensure(&info, info_size) == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}
	memset(info.s, 0, info_size);
	opt = 0;
#if defined(HAVE__CTIME64_S)
	{
		__time64_t iso9660_birth_time_tmp = (__time64_t) iso9660->birth_time; //time_t may be shorter than 64 bits
		_ctime64_s(buf, sizeof(buf), &(iso9660_birth_time_tmp));
	}
#elif defined(HAVE_CTIME_R)
	ctime_r(&(iso9660->birth_time), buf);
#else
	strncpy(buf, ctime(&(iso9660->birth_time)), sizeof(buf)-1);
	buf[sizeof(buf)-1] = '\0';
#endif
	archive_string_sprintf(&info,
	    "INFO %s%s", buf, archive_version_string());
	if (iso9660->opt.abstract_file != OPT_ABSTRACT_FILE_DEFAULT)
		set_option_info(&info, &opt, "abstract-file",
		    KEY_STR, iso9660->abstract_file_identifier.s);
	if (iso9660->opt.application_id != OPT_APPLICATION_ID_DEFAULT)
		set_option_info(&info, &opt, "application-id",
		    KEY_STR, iso9660->application_identifier.s);
	if (iso9660->opt.allow_vernum != OPT_ALLOW_VERNUM_DEFAULT)
		set_option_info(&info, &opt, "allow-vernum",
		    KEY_FLG, iso9660->opt.allow_vernum);
	if (iso9660->opt.biblio_file != OPT_BIBLIO_FILE_DEFAULT)
		set_option_info(&info, &opt, "biblio-file",
		    KEY_STR, iso9660->bibliographic_file_identifier.s);
	if (iso9660->opt.boot != OPT_BOOT_DEFAULT)
		set_option_info(&info, &opt, "boot",
		    KEY_STR, iso9660->el_torito.boot_filename.s);
	if (iso9660->opt.boot_catalog != OPT_BOOT_CATALOG_DEFAULT)
		set_option_info(&info, &opt, "boot-catalog",
		    KEY_STR, iso9660->el_torito.catalog_filename.s);
	if (iso9660->opt.boot_info_table != OPT_BOOT_INFO_TABLE_DEFAULT)
		set_option_info(&info, &opt, "boot-info-table",
		    KEY_FLG, iso9660->opt.boot_info_table);
	if (iso9660->opt.boot_load_seg != OPT_BOOT_LOAD_SEG_DEFAULT)
		set_option_info(&info, &opt, "boot-load-seg",
		    KEY_HEX, iso9660->el_torito.boot_load_seg);
	if (iso9660->opt.boot_load_size != OPT_BOOT_LOAD_SIZE_DEFAULT)
		set_option_info(&info, &opt, "boot-load-size",
		    KEY_INT, iso9660->el_torito.boot_load_size);
	if (iso9660->opt.boot_type != OPT_BOOT_TYPE_DEFAULT) {
		v = "no-emulation";
		if (iso9660->opt.boot_type == OPT_BOOT_TYPE_FD)
			v = "fd";
		if (iso9660->opt.boot_type == OPT_BOOT_TYPE_HARD_DISK)
			v = "hard-disk";
		set_option_info(&info, &opt, "boot-type",
		    KEY_STR, v);
	}
#ifdef HAVE_ZLIB_H
	if (iso9660->opt.compression_level != OPT_COMPRESSION_LEVEL_DEFAULT)
		set_option_info(&info, &opt, "compression-level",
		    KEY_INT, iso9660->zisofs.compression_level);
#endif
	if (iso9660->opt.copyright_file != OPT_COPYRIGHT_FILE_DEFAULT)
		set_option_info(&info, &opt, "copyright-file",
		    KEY_STR, iso9660->copyright_file_identifier.s);
	if (iso9660->opt.iso_level != OPT_ISO_LEVEL_DEFAULT)
		set_option_info(&info, &opt, "iso-level",
		    KEY_INT, iso9660->opt.iso_level);
	if (iso9660->opt.joliet != OPT_JOLIET_DEFAULT) {
		if (iso9660->opt.joliet == OPT_JOLIET_LONGNAME)
			set_option_info(&info, &opt, "joliet",
			    KEY_STR, "long");
		else
			set_option_info(&info, &opt, "joliet",
			    KEY_FLG, iso9660->opt.joliet);
	}
	if (iso9660->opt.limit_depth != OPT_LIMIT_DEPTH_DEFAULT)
		set_option_info(&info, &opt, "limit-depth",
		    KEY_FLG, iso9660->opt.limit_depth);
	if (iso9660->opt.limit_dirs != OPT_LIMIT_DIRS_DEFAULT)
		set_option_info(&info, &opt, "limit-dirs",
		    KEY_FLG, iso9660->opt.limit_dirs);
	if (iso9660->opt.pad != OPT_PAD_DEFAULT)
		set_option_info(&info, &opt, "pad",
		    KEY_FLG, iso9660->opt.pad);
	if (iso9660->opt.publisher != OPT_PUBLISHER_DEFAULT)
		set_option_info(&info, &opt, "publisher",
		    KEY_STR, iso9660->publisher_identifier.s);
	if (iso9660->opt.rr != OPT_RR_DEFAULT) {
		if (iso9660->opt.rr == OPT_RR_DISABLED)
			set_option_info(&info, &opt, "rockridge",
			    KEY_FLG, iso9660->opt.rr);
		else if (iso9660->opt.rr == OPT_RR_STRICT)
			set_option_info(&info, &opt, "rockridge",
			    KEY_STR, "strict");
		else if (iso9660->opt.rr == OPT_RR_USEFUL)
			set_option_info(&info, &opt, "rockridge",
			    KEY_STR, "useful");
	}
	if (iso9660->opt.volume_id != OPT_VOLUME_ID_DEFAULT)
		set_option_info(&info, &opt, "volume-id",
		    KEY_STR, iso9660->volume_identifier.s);
	if (iso9660->opt.zisofs != OPT_ZISOFS_DEFAULT)
		set_option_info(&info, &opt, "zisofs",
		    KEY_FLG, iso9660->opt.zisofs);

	memcpy(wb_buffptr(a), info.s, info_size);
	archive_string_free(&info);
	return (wb_consume(a, info_size));
}