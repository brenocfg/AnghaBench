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
typedef  void* u8 ;
struct ieee802_1x_mka_participant {void* orx; void* otx; void* oan; int /*<<< orphan*/  oki; } ;
struct ieee802_1x_mka_ki {scalar_t__ kn; } ;
struct ieee802_1x_kay {void* orx_an; void* otx_an; scalar_t__ orx_kn; scalar_t__ otx_kn; } ;
typedef  void* Boolean ;

/* Variables and functions */
 struct ieee802_1x_mka_participant* ieee802_1x_kay_get_principal_participant (struct ieee802_1x_kay*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,struct ieee802_1x_mka_ki*,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int ieee802_1x_kay_set_old_sa_attr(struct ieee802_1x_kay *kay,
				   struct ieee802_1x_mka_ki *oki,
				   u8 oan, Boolean otx, Boolean orx)
{
	struct ieee802_1x_mka_participant *principal;

	principal = ieee802_1x_kay_get_principal_participant(kay);
	if (!principal)
		return -1;

	if (!oki)
		os_memset(&principal->oki, 0, sizeof(principal->oki));
	else
		os_memcpy(&principal->oki, oki, sizeof(principal->oki));

	principal->oan = oan;
	principal->otx = otx;
	principal->orx = orx;

	if (!oki) {
		kay->otx_kn = 0;
		kay->orx_kn = 0;
	} else {
		kay->otx_kn = oki->kn;
		kay->orx_kn = oki->kn;
	}
	kay->otx_an = oan;
	kay->orx_an = oan;

	return 0;
}