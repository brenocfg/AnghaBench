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
typedef  int /*<<< orphan*/  Output ;

/* Variables and functions */
 int /*<<< orphan*/ * get_output_by_name (char*,int) ; 
 char* output_primary_name (int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static char *canonicalize_output_name(char *name) {
    /* Do not canonicalize special output names. */
    if (strcasecmp(name, "primary") == 0) {
        return name;
    }
    Output *output = get_output_by_name(name, false);
    return output ? output_primary_name(output) : name;
}