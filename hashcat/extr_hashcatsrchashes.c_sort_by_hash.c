#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  salt_t ;
struct TYPE_3__ {int is_salted; } ;
typedef  TYPE_1__ hashconfig_t ;
struct TYPE_4__ {void* digest; int /*<<< orphan*/ * salt; } ;
typedef  TYPE_2__ hash_t ;

/* Variables and functions */
 int sort_by_digest_p0p1 (void const*,void const*,void*) ; 
 int sort_by_salt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int sort_by_hash (const void *v1, const void *v2, void *v3)
{
  const hash_t *h1 = (const hash_t *) v1;
  const hash_t *h2 = (const hash_t *) v2;

  hashconfig_t *hashconfig = (hashconfig_t *) v3;

  if (hashconfig->is_salted == true)
  {
    const salt_t *s1 = h1->salt;
    const salt_t *s2 = h2->salt;

    int res = sort_by_salt (s1, s2);

    if (res != 0) return (res);
  }

  const void *d1 = h1->digest;
  const void *d2 = h2->digest;

  return sort_by_digest_p0p1 (d1, d2, v3);
}