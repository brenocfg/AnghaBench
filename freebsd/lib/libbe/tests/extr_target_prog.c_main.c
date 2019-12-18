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
typedef  int /*<<< orphan*/  libbe_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char*) ; 
 int be_create_depth (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * libbe_init (char*) ; 
 int /*<<< orphan*/  libbe_print_on_error (int /*<<< orphan*/ *,int) ; 

int main(int argc, char *argv[]) {

        libbe_handle_t *lbh;

	if (argc != 5)
		return -1;

        if ((lbh = libbe_init(argv[1])) == NULL)
                return -1;

	libbe_print_on_error(lbh, true);

	return (be_create_depth(lbh, argv[2], argv[3], atoi(argv[4])));
}