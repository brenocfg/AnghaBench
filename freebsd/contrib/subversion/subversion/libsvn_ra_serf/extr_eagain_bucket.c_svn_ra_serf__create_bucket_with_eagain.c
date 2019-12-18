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
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
struct TYPE_4__ {char const* data; int /*<<< orphan*/  remaining; } ;
typedef  TYPE_1__ eagain_baton_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  delay_bucket_vtable ; 
 int /*<<< orphan*/ * serf_bucket_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* serf_bucket_mem_alloc (int /*<<< orphan*/ *,int) ; 

serf_bucket_t *
svn_ra_serf__create_bucket_with_eagain(const char *data,
                                       apr_size_t len,
                                       serf_bucket_alloc_t *allocator)
{
  eagain_baton_t *eab;

  eab = serf_bucket_mem_alloc(allocator, sizeof(*eab));
  eab->data = data;
  eab->remaining = len;

  return serf_bucket_create(&delay_bucket_vtable, allocator, eab);
}