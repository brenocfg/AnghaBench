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
struct xml_ctx {scalar_t__ cdata; int /*<<< orphan*/  name; scalar_t__ userData; } ;
struct remote_lock {char* tmpfile_suffix; void* token; int /*<<< orphan*/  timeout; void* owner; } ;
typedef  int /*<<< orphan*/  git_hash_ctx ;
struct TYPE_2__ {int /*<<< orphan*/  hexsz; int /*<<< orphan*/  (* final_fn ) (unsigned char*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* update_fn ) (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* init_fn ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DAV_ACTIVELOCK_OWNER ; 
 int /*<<< orphan*/  DAV_ACTIVELOCK_TIMEOUT ; 
 int /*<<< orphan*/  DAV_ACTIVELOCK_TOKEN ; 
 int GIT_MAX_RAWSZ ; 
 int /*<<< orphan*/  hash_to_hex (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skip_prefix (scalar_t__,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (void*) ; 
 int /*<<< orphan*/  strtol (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (unsigned char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* the_hash_algo ; 
 void* xstrdup (scalar_t__) ; 

__attribute__((used)) static void handle_new_lock_ctx(struct xml_ctx *ctx, int tag_closed)
{
	struct remote_lock *lock = (struct remote_lock *)ctx->userData;
	git_hash_ctx hash_ctx;
	unsigned char lock_token_hash[GIT_MAX_RAWSZ];

	if (tag_closed && ctx->cdata) {
		if (!strcmp(ctx->name, DAV_ACTIVELOCK_OWNER)) {
			lock->owner = xstrdup(ctx->cdata);
		} else if (!strcmp(ctx->name, DAV_ACTIVELOCK_TIMEOUT)) {
			const char *arg;
			if (skip_prefix(ctx->cdata, "Second-", &arg))
				lock->timeout = strtol(arg, NULL, 10);
		} else if (!strcmp(ctx->name, DAV_ACTIVELOCK_TOKEN)) {
			lock->token = xstrdup(ctx->cdata);

			the_hash_algo->init_fn(&hash_ctx);
			the_hash_algo->update_fn(&hash_ctx, lock->token, strlen(lock->token));
			the_hash_algo->final_fn(lock_token_hash, &hash_ctx);

			lock->tmpfile_suffix[0] = '_';
			memcpy(lock->tmpfile_suffix + 1, hash_to_hex(lock_token_hash), the_hash_algo->hexsz);
		}
	}
}