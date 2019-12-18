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
struct sec_softc {int dummy; } ;
struct sec_session {int dummy; } ;
struct sec_hw_desc {int shd_dir; int /*<<< orphan*/  shd_mode0; int /*<<< orphan*/  shd_eu_sel0; } ;
struct sec_desc {struct sec_hw_desc* sd_desc; } ;
struct cryptop {int dummy; } ;
struct cryptodesc {int crd_alg; int crd_flags; } ;

/* Variables and functions */
 int CRD_F_ENCRYPT ; 
#define  CRYPTO_3DES_CBC 129 
#define  CRYPTO_DES_CBC 128 
 int EINVAL ; 
 int /*<<< orphan*/  SEC_DEU_MODE_CBC ; 
 int /*<<< orphan*/  SEC_DEU_MODE_ED ; 
 int /*<<< orphan*/  SEC_DEU_MODE_TS ; 
 int /*<<< orphan*/  SEC_EU_DEU ; 
 int sec_build_common_ns_desc (struct sec_softc*,struct sec_desc*,struct sec_session*,struct cryptop*,struct cryptodesc*,int) ; 
 int sec_build_common_s_desc (struct sec_softc*,struct sec_desc*,struct sec_session*,struct cryptop*,struct cryptodesc*,struct cryptodesc*,int) ; 
 int sec_split_crp (struct cryptop*,struct cryptodesc**,struct cryptodesc**) ; 

__attribute__((used)) static int
sec_deu_make_desc(struct sec_softc *sc, struct sec_session *ses,
    struct sec_desc *desc, struct cryptop *crp, int buftype)
{
	struct sec_hw_desc *hd = desc->sd_desc;
	struct cryptodesc *enc, *mac;
	int error;

	error = sec_split_crp(crp, &enc, &mac);
	if (error)
		return (error);

	if (!enc)
		return (EINVAL);

	hd->shd_eu_sel0 = SEC_EU_DEU;
	hd->shd_mode0 = SEC_DEU_MODE_CBC;

	switch (enc->crd_alg) {
	case CRYPTO_3DES_CBC:
		hd->shd_mode0 |= SEC_DEU_MODE_TS;
		break;
	case CRYPTO_DES_CBC:
		break;
	default:
		return (EINVAL);
	}

	if (enc->crd_flags & CRD_F_ENCRYPT) {
		hd->shd_mode0 |= SEC_DEU_MODE_ED;
		hd->shd_dir = 0;
	} else
		hd->shd_dir = 1;

	if (mac)
		error = sec_build_common_s_desc(sc, desc, ses, crp, enc, mac,
		    buftype);
	else
		error = sec_build_common_ns_desc(sc, desc, ses, crp, enc,
		    buftype);

	return (error);
}