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
typedef  int /*<<< orphan*/  TCLIST ;

/* Variables and functions */
 int /*<<< orphan*/ * tcbdbget4 (void*,int*,int) ; 

__attribute__((used)) static TCLIST *
get_itcli (void *hash, int key)
{
  TCLIST *list = NULL;

  if (!hash)
    return NULL;

  /* key found, return current value */
  if ((list = tcbdbget4 (hash, &key, sizeof (int))) != NULL)
    return list;

  return NULL;
}