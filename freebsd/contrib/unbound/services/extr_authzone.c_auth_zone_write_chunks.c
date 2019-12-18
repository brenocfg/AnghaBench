#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct auth_xfer {TYPE_1__* task_transfer; } ;
struct auth_chunk {int /*<<< orphan*/  len; scalar_t__ data; struct auth_chunk* next; } ;
struct TYPE_2__ {struct auth_chunk* chunks_first; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  log_err (char*,char const*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
auth_zone_write_chunks(struct auth_xfer* xfr, const char* fname)
{
	FILE* out;
	struct auth_chunk* p;
	out = fopen(fname, "w");
	if(!out) {
		log_err("could not open %s: %s", fname, strerror(errno));
		return 0;
	}
	for(p = xfr->task_transfer->chunks_first; p ; p = p->next) {
		if(!write_out(out, (char*)p->data, p->len)) {
			log_err("could not write http download to %s", fname);
			fclose(out);
			return 0;
		}
	}
	fclose(out);
	return 1;
}