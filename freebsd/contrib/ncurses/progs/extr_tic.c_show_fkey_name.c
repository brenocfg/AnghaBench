#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ keycode; char* name; } ;
typedef  TYPE_1__ NAME_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* keyname (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
show_fkey_name(NAME_VALUE * data)
{
    if (data->keycode > 0) {
	fprintf(stderr, " %s", keyname(data->keycode));
	fprintf(stderr, " (capability \"%s\")", data->name);
    } else {
	fprintf(stderr, " capability \"%s\"", data->name);
    }
}