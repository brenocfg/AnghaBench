#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* digest; } ;
typedef  TYPE_1__ hash_t ;

/* Variables and functions */
 int sort_by_digest_p0p1 (void const*,void const*,void*) ; 

int sort_by_hash_no_salt (const void *v1, const void *v2, void *v3)
{
  const hash_t *h1 = (const hash_t *) v1;
  const hash_t *h2 = (const hash_t *) v2;

  const void *d1 = h1->digest;
  const void *d2 = h2->digest;

  return sort_by_digest_p0p1 (d1, d2, v3);
}