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
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* serf_bucket_mem_alloc (int /*<<< orphan*/ *,int) ; 

char *serf_bstrmemdup(serf_bucket_alloc_t *allocator,
                      const char *str,
                      apr_size_t size)
{
    char *newstr = serf_bucket_mem_alloc(allocator, size + 1);
    memcpy(newstr, str, size);
    newstr[size] = '\0';
    return newstr;
}