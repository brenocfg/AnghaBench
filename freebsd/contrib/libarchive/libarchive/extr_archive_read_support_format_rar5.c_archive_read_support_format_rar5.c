#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rar5 {int dummy; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int __archive_read_register_format (struct archive_read*,struct rar5*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct archive_read*),int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int get_archive_read (struct archive*,struct archive_read**) ; 
 struct rar5* malloc (int) ; 
 int /*<<< orphan*/  rar5_bid ; 
 int /*<<< orphan*/  rar5_capabilities ; 
 int /*<<< orphan*/  rar5_cleanup (struct archive_read*) ; 
 int /*<<< orphan*/  rar5_has_encrypted_entries ; 
 int rar5_init (struct rar5*) ; 
 int /*<<< orphan*/  rar5_options ; 
 int /*<<< orphan*/  rar5_read_data ; 
 int /*<<< orphan*/  rar5_read_data_skip ; 
 int /*<<< orphan*/  rar5_read_header ; 
 int /*<<< orphan*/  rar5_seek_data ; 

int archive_read_support_format_rar5(struct archive *_a) {
	struct archive_read* ar;
	int ret;
	struct rar5* rar;

	if(ARCHIVE_OK != (ret = get_archive_read(_a, &ar)))
		return ret;

	rar = malloc(sizeof(*rar));
	if(rar == NULL) {
		archive_set_error(&ar->archive, ENOMEM,
		    "Can't allocate rar5 data");
		return ARCHIVE_FATAL;
	}

	if(ARCHIVE_OK != rar5_init(rar)) {
		archive_set_error(&ar->archive, ENOMEM,
		    "Can't allocate rar5 filter buffer");
		return ARCHIVE_FATAL;
	}

	ret = __archive_read_register_format(ar,
	    rar,
	    "rar5",
	    rar5_bid,
	    rar5_options,
	    rar5_read_header,
	    rar5_read_data,
	    rar5_read_data_skip,
	    rar5_seek_data,
	    rar5_cleanup,
	    rar5_capabilities,
	    rar5_has_encrypted_entries);

	if(ret != ARCHIVE_OK) {
		(void) rar5_cleanup(ar);
	}

	return ret;
}