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
typedef  int /*<<< orphan*/  u_char ;
struct hmac_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  G_ELI_DEBUG (int,char*,char*,...) ; 
 int /*<<< orphan*/  MODINFO_NAME ; 
 int /*<<< orphan*/  g_eli_crypto_hmac_update (struct hmac_ctx*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * preload_fetch_addr (int /*<<< orphan*/ *) ; 
 size_t preload_fetch_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * preload_search_by_type (char*) ; 
 char* preload_search_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

__attribute__((used)) static int
g_eli_keyfiles_load(struct hmac_ctx *ctx, const char *provider)
{
	u_char *keyfile, *data;
	char *file, name[64];
	size_t size;
	int i;

	for (i = 0; ; i++) {
		snprintf(name, sizeof(name), "%s:geli_keyfile%d", provider, i);
		keyfile = preload_search_by_type(name);
		if (keyfile == NULL && i == 0) {
			/*
			 * If there is only one keyfile, allow simpler name.
			 */
			snprintf(name, sizeof(name), "%s:geli_keyfile", provider);
			keyfile = preload_search_by_type(name);
		}
		if (keyfile == NULL)
			return (i);	/* Return number of loaded keyfiles. */
		data = preload_fetch_addr(keyfile);
		if (data == NULL) {
			G_ELI_DEBUG(0, "Cannot find key file data for %s.",
			    name);
			return (0);
		}
		size = preload_fetch_size(keyfile);
		if (size == 0) {
			G_ELI_DEBUG(0, "Cannot find key file size for %s.",
			    name);
			return (0);
		}
		file = preload_search_info(keyfile, MODINFO_NAME);
		if (file == NULL) {
			G_ELI_DEBUG(0, "Cannot find key file name for %s.",
			    name);
			return (0);
		}
		G_ELI_DEBUG(1, "Loaded keyfile %s for %s (type: %s).", file,
		    provider, name);
		g_eli_crypto_hmac_update(ctx, data, size);
	}
}