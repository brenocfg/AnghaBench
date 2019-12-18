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
struct sa_open_data {int tmp_size; scalar_t__ tmp_length; struct ipv4_range* tmp_base; } ;
struct ipv4_range {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int __touch_tmp_base(struct sa_open_data *od, gfp_t gfp)
{
	if (!od->tmp_base) {
		/**
		 * Allocate a temporary table with twice the size of the previous
		 *  table or at least 100, on which new entries can be inserted.
		 */
		if (od->tmp_size < 100)
			od->tmp_size = 100;
		od->tmp_base = (struct ipv4_range *)malloc(
			sizeof(struct ipv4_range) * od->tmp_size /*, gfp*/ );
		if (!od->tmp_base) {
			fprintf(stderr,
				"salist: cannot allocate the temporary list for enlarging it.\n");
			return -ENOMEM;
		}
		od->tmp_length = 0;
	}
	return 0;
}