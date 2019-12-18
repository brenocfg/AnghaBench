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
struct TYPE_3__ {int buckets; int /*<<< orphan*/ ** table; } ;
typedef  TYPE_1__ hashtable_t ;
typedef  int /*<<< orphan*/  hashchain_t ;

/* Variables and functions */
 int abs (int) ; 

__attribute__((used)) static hashchain_t *hashtable_get (hashtable_t *H, int hashvalue)
{
  hashvalue = (abs(hashvalue) % H->buckets);
  return (H->table[hashvalue]);
}