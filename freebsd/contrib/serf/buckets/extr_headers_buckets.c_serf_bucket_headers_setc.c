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
typedef  int /*<<< orphan*/  serf_bucket_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf_bucket_headers_setx (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void serf_bucket_headers_setc(
    serf_bucket_t *headers_bucket,
    const char *header,
    const char *value)
{
    serf_bucket_headers_setx(headers_bucket,
                             header, strlen(header), 1,
                             value, strlen(value), 1);
}