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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hex_encode (void const*,size_t,char**) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
hex_dump_data(const void *data, size_t length)
{
    char *p;

    hex_encode(data, length, &p);
    printf("%s\n", p);
    free(p);
}