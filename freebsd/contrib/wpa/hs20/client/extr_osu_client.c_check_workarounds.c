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
struct hs20_osu_client {unsigned long workarounds; int /*<<< orphan*/  http; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int WORKAROUND_OCSP_OPTIONAL ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  http_ocsp_set (int /*<<< orphan*/ ,int) ; 
 unsigned long strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static void check_workarounds(struct hs20_osu_client *ctx)
{
	FILE *f;
	char buf[100];
	unsigned long int val = 0;

	f = fopen("hs20-osu-client.workarounds", "r");
	if (f == NULL)
		return;

	if (fgets(buf, sizeof(buf), f))
		val = strtoul(buf, NULL, 16);

	fclose(f);

	if (val) {
		wpa_printf(MSG_INFO, "Workarounds enabled: 0x%lx", val);
		ctx->workarounds = val;
		if (ctx->workarounds & WORKAROUND_OCSP_OPTIONAL)
			http_ocsp_set(ctx->http, 1);
	}
}