#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  filename; TYPE_3__* key; } ;
typedef  TYPE_1__ Identity ;

/* Variables and functions */
 scalar_t__ KEY_RSA ; 
 int SSH_BUG_RSASIGMD5 ; 
 int datafellows ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshkey_type (TYPE_3__*) ; 
 scalar_t__ sshkey_type_plain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
try_identity(Identity *id)
{
	if (!id->key)
		return (0);
	if (sshkey_type_plain(id->key->type) == KEY_RSA &&
	    (datafellows & SSH_BUG_RSASIGMD5) != 0) {
		debug("Skipped %s key %s for RSA/MD5 server",
		    sshkey_type(id->key), id->filename);
		return (0);
	}
	return 1;
}