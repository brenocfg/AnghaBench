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
struct hmac_ctx {int dummy; } ;
struct gctl_req {int dummy; } ;
struct g_eli_metadata {int dummy; } ;

/* Variables and functions */
 int eli_genkey_files (struct gctl_req*,int,char*,struct hmac_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int eli_genkey_passphrase (struct gctl_req*,struct g_eli_metadata*,int,struct hmac_ctx*) ; 
 int /*<<< orphan*/  g_eli_crypto_hmac_final (struct hmac_ctx*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_eli_crypto_hmac_init (struct hmac_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 

__attribute__((used)) static unsigned char *
eli_genkey(struct gctl_req *req, struct g_eli_metadata *md, unsigned char *key,
    bool new)
{
	struct hmac_ctx ctx;
	bool nopassphrase;
	int nfiles;

	nopassphrase =
	    gctl_get_int(req, new ? "nonewpassphrase" : "nopassphrase");

	g_eli_crypto_hmac_init(&ctx, NULL, 0);

	nfiles = eli_genkey_files(req, new, "keyfile", &ctx, NULL, 0);
	if (nfiles == -1)
		return (NULL);
	else if (nfiles == 0 && nopassphrase) {
		gctl_error(req, "No key components given.");
		return (NULL);
	}

	if (eli_genkey_passphrase(req, md, new, &ctx) == -1)
		return (NULL);

	g_eli_crypto_hmac_final(&ctx, key, 0);

	return (key);
}