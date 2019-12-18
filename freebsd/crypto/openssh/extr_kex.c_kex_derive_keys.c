#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sshbuf {int dummy; } ;
struct ssh {struct kex* kex; } ;
struct kex {TYPE_3__** newkeys; scalar_t__ server; int /*<<< orphan*/  we_need; } ;
struct TYPE_5__ {int /*<<< orphan*/ * key; } ;
struct TYPE_4__ {int /*<<< orphan*/ * key; int /*<<< orphan*/ * iv; } ;
struct TYPE_6__ {TYPE_2__ mac; TYPE_1__ enc; } ;

/* Variables and functions */
 int MODE_IN ; 
 int MODE_MAX ; 
 int MODE_OUT ; 
 int NKEYS ; 
 int derive_key (struct ssh*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct sshbuf const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

int
kex_derive_keys(struct ssh *ssh, u_char *hash, u_int hashlen,
    const struct sshbuf *shared_secret)
{
	struct kex *kex = ssh->kex;
	u_char *keys[NKEYS];
	u_int i, j, mode, ctos;
	int r;

	for (i = 0; i < NKEYS; i++) {
		if ((r = derive_key(ssh, 'A'+i, kex->we_need, hash, hashlen,
		    shared_secret, &keys[i])) != 0) {
			for (j = 0; j < i; j++)
				free(keys[j]);
			return r;
		}
	}
	for (mode = 0; mode < MODE_MAX; mode++) {
		ctos = (!kex->server && mode == MODE_OUT) ||
		    (kex->server && mode == MODE_IN);
		kex->newkeys[mode]->enc.iv  = keys[ctos ? 0 : 1];
		kex->newkeys[mode]->enc.key = keys[ctos ? 2 : 3];
		kex->newkeys[mode]->mac.key = keys[ctos ? 4 : 5];
	}
	return 0;
}