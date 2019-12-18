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
struct mg_thread_ctx {int /*<<< orphan*/  min_error; int /*<<< orphan*/  maj_error; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mg_thread_ctx*) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
destroy_context(void *ptr)
{
    struct mg_thread_ctx *mg = ptr;
    OM_uint32 junk;

    if (mg == NULL)
	return;

    gss_release_buffer(&junk, &mg->maj_error);
    gss_release_buffer(&junk, &mg->min_error);
    free(mg);
}