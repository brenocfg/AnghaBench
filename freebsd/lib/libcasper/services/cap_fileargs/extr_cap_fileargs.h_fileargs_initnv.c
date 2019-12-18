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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fileargs_t ;

/* Variables and functions */
 int /*<<< orphan*/  dnvlist_get_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fileargs_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_get_number (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline fileargs_t *
fileargs_initnv(nvlist_t *limits)
{
	fileargs_t *fa;

	fa = fileargs_init(0, NULL,
	    nvlist_get_number(limits, "flags"),
	    dnvlist_get_number(limits, "mode", 0),
	    NULL,
	    nvlist_get_number(limits, "operations"));
	nvlist_destroy(limits);

	return (fa);
}