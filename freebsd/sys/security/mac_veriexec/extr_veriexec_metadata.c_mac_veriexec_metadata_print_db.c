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
struct veriexec_devhead {int dummy; } ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  fpdbs ;

/* Variables and functions */
 int /*<<< orphan*/  mac_veriexec_print_db_head (struct sbuf*,struct veriexec_devhead*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char const*) ; 
 int /*<<< orphan*/  ve_mutex ; 
 int /*<<< orphan*/  veriexec_dev_head ; 
 int /*<<< orphan*/  veriexec_file_dev_head ; 

void
mac_veriexec_metadata_print_db(struct sbuf *sbp)
{
	struct {
		struct veriexec_devhead *h;
		const char *name;
	} fpdbs[] = {
		{ &veriexec_file_dev_head, "regular files" },
		{ &veriexec_dev_head, "executable files" },
	};
	int i;

	mtx_lock(&ve_mutex);
	for (i = 0; i < sizeof(fpdbs)/sizeof(fpdbs[0]); i++) {
		sbuf_printf(sbp, "%s fingerprint db:\n", fpdbs[i].name);
		mac_veriexec_print_db_head(sbp, fpdbs[i].h);
	}
	mtx_unlock(&ve_mutex);
}