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
struct mppe_state {int /*<<< orphan*/  sesskey; int /*<<< orphan*/  keylen; int /*<<< orphan*/  mastkey; } ;
typedef  int /*<<< orphan*/  RC4_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  GetNewKeyFromSHA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MPPEReduceSessionKey (struct mppe_state*) ; 
 int MPPE_KEY_LEN ; 
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
MPPEKeyChange(struct mppe_state *mp)
{
  char InterimKey[MPPE_KEY_LEN];
  RC4_KEY RC4Key;

  GetNewKeyFromSHA(mp->mastkey, mp->sesskey, mp->keylen, InterimKey);
  RC4_set_key(&RC4Key, mp->keylen, InterimKey);
  RC4(&RC4Key, mp->keylen, InterimKey, mp->sesskey);

  MPPEReduceSessionKey(mp);
}