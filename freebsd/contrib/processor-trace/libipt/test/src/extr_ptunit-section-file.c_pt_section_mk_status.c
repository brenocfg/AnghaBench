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
typedef  scalar_t__ uint64_t ;
struct pt_file_status {long size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 struct pt_file_status* malloc (int) ; 
 int pte_bad_image ; 
 int pte_internal ; 
 int pte_nomem ; 

int pt_section_mk_status(void **pstatus, uint64_t *psize, const char *filename)
{
	struct pt_file_status *status;
	FILE *file;
	long size;
	int errcode;

	if (!pstatus || !psize)
		return -pte_internal;

	file = fopen(filename, "rb");
	if (!file)
		return -pte_bad_image;

	errcode = fseek(file, 0, SEEK_END);
	if (errcode) {
		errcode = -pte_bad_image;
		goto out_file;
	}

	size = ftell(file);
	if (size < 0) {
		errcode = -pte_bad_image;
		goto out_file;
	}

	status = malloc(sizeof(*status));
	if (!status) {
		errcode = -pte_nomem;
		goto out_file;
	}

	status->size = size;

	*pstatus = status;
	*psize = (uint64_t) size;

	errcode = 0;

out_file:
	fclose(file);
	return errcode;
}