#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__* s; } ;
struct TYPE_14__ {TYPE_6__* rootent; int /*<<< orphan*/ * pathtbl; int /*<<< orphan*/  vdd_type; scalar_t__ max_depth; } ;
struct TYPE_13__ {int /*<<< orphan*/  zisofs; int /*<<< orphan*/  volume_id; int /*<<< orphan*/  rr; int /*<<< orphan*/  publisher; int /*<<< orphan*/  pad; int /*<<< orphan*/  limit_dirs; int /*<<< orphan*/  limit_depth; int /*<<< orphan*/  joliet; int /*<<< orphan*/  iso_level; int /*<<< orphan*/  copyright_file; int /*<<< orphan*/  compression_level; int /*<<< orphan*/  boot_type; int /*<<< orphan*/  boot_load_size; int /*<<< orphan*/  boot_load_seg; int /*<<< orphan*/  boot_info_table; int /*<<< orphan*/  boot_catalog; int /*<<< orphan*/  boot; int /*<<< orphan*/  biblio_file; int /*<<< orphan*/  allow_vernum; int /*<<< orphan*/  application_id; int /*<<< orphan*/  abstract_file; } ;
struct TYPE_12__ {int compression_level; int /*<<< orphan*/  stream; scalar_t__ stream_valid; scalar_t__ block_pointers_allocated; int /*<<< orphan*/ * block_pointers; } ;
struct TYPE_16__ {int /*<<< orphan*/  boot_load_size; scalar_t__ boot_load_seg; TYPE_7__ id; int /*<<< orphan*/  platform_id; int /*<<< orphan*/ * boot; TYPE_7__ boot_filename; TYPE_7__ catalog_filename; int /*<<< orphan*/ * catalog; } ;
struct TYPE_15__ {int /*<<< orphan*/ * pathtbl; int /*<<< orphan*/  vdd_type; scalar_t__ max_depth; int /*<<< orphan*/ * rootent; } ;
struct iso9660 {int temp_fd; int dircnt_max; int /*<<< orphan*/ * sconv_from_utf16be; int /*<<< orphan*/ * sconv_to_utf16be; TYPE_7__ cur_dirstr; TYPE_3__ primary; TYPE_6__* cur_dirent; TYPE_2__ opt; TYPE_1__ zisofs; TYPE_5__ el_torito; TYPE_7__ bibliographic_file_identifier; TYPE_7__ abstract_file_identifier; TYPE_7__ copyright_file_identifier; TYPE_7__ application_identifier; TYPE_7__ data_preparer_identifier; TYPE_7__ publisher_identifier; TYPE_7__ volume_identifier; TYPE_7__ mbs; TYPE_7__ utf16be; scalar_t__ wbuff_tail; scalar_t__ wbuff_written; scalar_t__ wbuff_offset; int /*<<< orphan*/  wbuff_type; int /*<<< orphan*/  wbuff_remaining; int /*<<< orphan*/ * directories_too_deep; TYPE_4__ joliet; int /*<<< orphan*/ * cur_file; scalar_t__ birth_time; } ;
struct TYPE_11__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_write {char* format_name; TYPE_10__ archive; int /*<<< orphan*/  (* format_free ) (struct archive_write*) ;int /*<<< orphan*/  format_close; int /*<<< orphan*/  format_finish_entry; int /*<<< orphan*/  format_write_data; int /*<<< orphan*/  format_write_header; int /*<<< orphan*/  format_options; struct iso9660* format_data; } ;
struct archive {int dummy; } ;
struct TYPE_17__ {struct TYPE_17__* parent; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_ISO9660 ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  BOOT_LOAD_SIZE ; 
 int /*<<< orphan*/  BOOT_PLATFORM_X86 ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  OPT_ABSTRACT_FILE_DEFAULT ; 
 int /*<<< orphan*/  OPT_ALLOW_VERNUM_DEFAULT ; 
 int /*<<< orphan*/  OPT_APPLICATION_ID_DEFAULT ; 
 int /*<<< orphan*/  OPT_BIBLIO_FILE_DEFAULT ; 
 int /*<<< orphan*/  OPT_BOOT_CATALOG_DEFAULT ; 
 int /*<<< orphan*/  OPT_BOOT_DEFAULT ; 
 int /*<<< orphan*/  OPT_BOOT_INFO_TABLE_DEFAULT ; 
 int /*<<< orphan*/  OPT_BOOT_LOAD_SEG_DEFAULT ; 
 int /*<<< orphan*/  OPT_BOOT_LOAD_SIZE_DEFAULT ; 
 int /*<<< orphan*/  OPT_BOOT_TYPE_DEFAULT ; 
 int /*<<< orphan*/  OPT_COMPRESSION_LEVEL_DEFAULT ; 
 int /*<<< orphan*/  OPT_COPYRIGHT_FILE_DEFAULT ; 
 int /*<<< orphan*/  OPT_ISO_LEVEL_DEFAULT ; 
 int /*<<< orphan*/  OPT_JOLIET_DEFAULT ; 
 int /*<<< orphan*/  OPT_LIMIT_DEPTH_DEFAULT ; 
 int /*<<< orphan*/  OPT_LIMIT_DIRS_DEFAULT ; 
 int /*<<< orphan*/  OPT_PAD_DEFAULT ; 
 int /*<<< orphan*/  OPT_PUBLISHER_DEFAULT ; 
 int /*<<< orphan*/  OPT_RR_DEFAULT ; 
 int /*<<< orphan*/  OPT_VOLUME_ID_DEFAULT ; 
 int /*<<< orphan*/  OPT_ZISOFS_DEFAULT ; 
 int /*<<< orphan*/  VDD_JOLIET ; 
 int /*<<< orphan*/  VDD_PRIMARY ; 
 int /*<<< orphan*/  WB_TO_TEMP ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_10__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_strcpy (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  archive_string_ensure (TYPE_7__*,int) ; 
 int /*<<< orphan*/  archive_string_init (TYPE_7__*) ; 
 char* archive_version_string () ; 
 struct iso9660* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct iso9660*) ; 
 int /*<<< orphan*/  iso9660_close ; 
 int /*<<< orphan*/  iso9660_finish_entry ; 
 int /*<<< orphan*/  iso9660_free (struct archive_write*) ; 
 int /*<<< orphan*/  iso9660_options ; 
 int /*<<< orphan*/  iso9660_write_data ; 
 int /*<<< orphan*/  iso9660_write_header ; 
 TYPE_6__* isoent_create_virtual_dir (struct archive_write*,struct iso9660*,char*) ; 
 int /*<<< orphan*/  isofile_init_entry_data_file_list (struct iso9660*) ; 
 int /*<<< orphan*/  isofile_init_entry_list (struct iso9660*) ; 
 int /*<<< orphan*/  isofile_init_hardlinks (struct iso9660*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct archive_write*) ; 
 int /*<<< orphan*/  wb_buffmax () ; 

int
archive_write_set_format_iso9660(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct iso9660 *iso9660;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_set_format_iso9660");

	/* If another format was already registered, unregister it. */
	if (a->format_free != NULL)
		(a->format_free)(a);

	iso9660 = calloc(1, sizeof(*iso9660));
	if (iso9660 == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate iso9660 data");
		return (ARCHIVE_FATAL);
	}
	iso9660->birth_time = 0;
	iso9660->temp_fd = -1;
	iso9660->cur_file = NULL;
	iso9660->primary.max_depth = 0;
	iso9660->primary.vdd_type = VDD_PRIMARY;
	iso9660->primary.pathtbl = NULL;
	iso9660->joliet.rootent = NULL;
	iso9660->joliet.max_depth = 0;
	iso9660->joliet.vdd_type = VDD_JOLIET;
	iso9660->joliet.pathtbl = NULL;
	isofile_init_entry_list(iso9660);
	isofile_init_entry_data_file_list(iso9660);
	isofile_init_hardlinks(iso9660);
	iso9660->directories_too_deep = NULL;
	iso9660->dircnt_max = 1;
	iso9660->wbuff_remaining = wb_buffmax();
	iso9660->wbuff_type = WB_TO_TEMP;
	iso9660->wbuff_offset = 0;
	iso9660->wbuff_written = 0;
	iso9660->wbuff_tail = 0;
	archive_string_init(&(iso9660->utf16be));
	archive_string_init(&(iso9660->mbs));

	/*
	 * Init Identifiers used for PVD and SVD.
	 */
	archive_string_init(&(iso9660->volume_identifier));
	archive_strcpy(&(iso9660->volume_identifier), "CDROM");
	archive_string_init(&(iso9660->publisher_identifier));
	archive_string_init(&(iso9660->data_preparer_identifier));
	archive_string_init(&(iso9660->application_identifier));
	archive_strcpy(&(iso9660->application_identifier),
	    archive_version_string());
	archive_string_init(&(iso9660->copyright_file_identifier));
	archive_string_init(&(iso9660->abstract_file_identifier));
	archive_string_init(&(iso9660->bibliographic_file_identifier));

	/*
	 * Init El Torito bootable CD variables.
	 */
	archive_string_init(&(iso9660->el_torito.catalog_filename));
	iso9660->el_torito.catalog = NULL;
	/* Set default file name of boot catalog  */
	archive_strcpy(&(iso9660->el_torito.catalog_filename),
	    "boot.catalog");
	archive_string_init(&(iso9660->el_torito.boot_filename));
	iso9660->el_torito.boot = NULL;
	iso9660->el_torito.platform_id = BOOT_PLATFORM_X86;
	archive_string_init(&(iso9660->el_torito.id));
	iso9660->el_torito.boot_load_seg = 0;
	iso9660->el_torito.boot_load_size = BOOT_LOAD_SIZE;

	/*
	 * Init zisofs variables.
	 */
#ifdef HAVE_ZLIB_H
	iso9660->zisofs.block_pointers = NULL;
	iso9660->zisofs.block_pointers_allocated = 0;
	iso9660->zisofs.stream_valid = 0;
	iso9660->zisofs.compression_level = 9;
	memset(&(iso9660->zisofs.stream), 0,
	    sizeof(iso9660->zisofs.stream));
#endif

	/*
	 * Set default value of iso9660 options.
	 */
	iso9660->opt.abstract_file = OPT_ABSTRACT_FILE_DEFAULT;
	iso9660->opt.application_id = OPT_APPLICATION_ID_DEFAULT;
	iso9660->opt.allow_vernum = OPT_ALLOW_VERNUM_DEFAULT;
	iso9660->opt.biblio_file = OPT_BIBLIO_FILE_DEFAULT;
	iso9660->opt.boot = OPT_BOOT_DEFAULT;
	iso9660->opt.boot_catalog = OPT_BOOT_CATALOG_DEFAULT;
	iso9660->opt.boot_info_table = OPT_BOOT_INFO_TABLE_DEFAULT;
	iso9660->opt.boot_load_seg = OPT_BOOT_LOAD_SEG_DEFAULT;
	iso9660->opt.boot_load_size = OPT_BOOT_LOAD_SIZE_DEFAULT;
	iso9660->opt.boot_type = OPT_BOOT_TYPE_DEFAULT;
	iso9660->opt.compression_level = OPT_COMPRESSION_LEVEL_DEFAULT;
	iso9660->opt.copyright_file = OPT_COPYRIGHT_FILE_DEFAULT;
	iso9660->opt.iso_level = OPT_ISO_LEVEL_DEFAULT;
	iso9660->opt.joliet = OPT_JOLIET_DEFAULT;
	iso9660->opt.limit_depth = OPT_LIMIT_DEPTH_DEFAULT;
	iso9660->opt.limit_dirs = OPT_LIMIT_DIRS_DEFAULT;
	iso9660->opt.pad = OPT_PAD_DEFAULT;
	iso9660->opt.publisher = OPT_PUBLISHER_DEFAULT;
	iso9660->opt.rr = OPT_RR_DEFAULT;
	iso9660->opt.volume_id = OPT_VOLUME_ID_DEFAULT;
	iso9660->opt.zisofs = OPT_ZISOFS_DEFAULT;

	/* Create the root directory. */
	iso9660->primary.rootent =
	    isoent_create_virtual_dir(a, iso9660, "");
	if (iso9660->primary.rootent == NULL) {
		free(iso9660);
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}
	iso9660->primary.rootent->parent = iso9660->primary.rootent;
	iso9660->cur_dirent = iso9660->primary.rootent;
	archive_string_init(&(iso9660->cur_dirstr));
	archive_string_ensure(&(iso9660->cur_dirstr), 1);
	iso9660->cur_dirstr.s[0] = 0;
	iso9660->sconv_to_utf16be = NULL;
	iso9660->sconv_from_utf16be = NULL;

	a->format_data = iso9660;
	a->format_name = "iso9660";
	a->format_options = iso9660_options;
	a->format_write_header = iso9660_write_header;
	a->format_write_data = iso9660_write_data;
	a->format_finish_entry = iso9660_finish_entry;
	a->format_close = iso9660_close;
	a->format_free = iso9660_free;
	a->archive.archive_format = ARCHIVE_FORMAT_ISO9660;
	a->archive.archive_format_name = "ISO9660";

	return (ARCHIVE_OK);
}