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
struct dpp_bootstrap_info {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPP_BOOTSTRAP_QR_CODE ; 
 struct dpp_bootstrap_info* dpp_parse_uri (char const*) ; 

struct dpp_bootstrap_info * dpp_parse_qr_code(const char *uri)
{
	struct dpp_bootstrap_info *bi;

	bi = dpp_parse_uri(uri);
	if (bi)
		bi->type = DPP_BOOTSTRAP_QR_CODE;
	return bi;
}