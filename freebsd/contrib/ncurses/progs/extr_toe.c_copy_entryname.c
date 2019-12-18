#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  d_name; } ;
typedef  TYPE_1__ DIRENT ;

/* Variables and functions */
 size_t NAMLEN (TYPE_1__*) ; 
 int /*<<< orphan*/  failed (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static char *
copy_entryname(DIRENT * src)
{
    size_t len = NAMLEN(src);
    char *result = malloc(len + 1);
    if (result == 0)
	failed("copy entryname");
    memcpy(result, src->d_name, len);
    result[len] = '\0';

    return result;
}