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
typedef  int /*<<< orphan*/  u32 ;
struct rsa_priv_f3_pdb {int /*<<< orphan*/  p_q_len; int /*<<< orphan*/  tmp2_dma; int /*<<< orphan*/  tmp1_dma; int /*<<< orphan*/  dq_dma; int /*<<< orphan*/  dp_dma; int /*<<< orphan*/  q_dma; int /*<<< orphan*/  p_dma; int /*<<< orphan*/  c_dma; int /*<<< orphan*/  f_dma; int /*<<< orphan*/  g_dma; int /*<<< orphan*/  sgf; } ;

/* Variables and functions */
 int OP_PCLID_RSADEC_PRVKEY ; 
 int OP_TYPE_UNI_PROTOCOL ; 
 int RSA_PRIV_KEY_FRM_3 ; 
 int /*<<< orphan*/  SIZEOF_RSA_PRIV_F3_PDB ; 
 int /*<<< orphan*/  append_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_operation (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  append_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_job_desc_pdb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void init_rsa_priv_f3_desc(u32 *desc, struct rsa_priv_f3_pdb *pdb)
{
	init_job_desc_pdb(desc, 0, SIZEOF_RSA_PRIV_F3_PDB);
	append_cmd(desc, pdb->sgf);
	append_ptr(desc, pdb->g_dma);
	append_ptr(desc, pdb->f_dma);
	append_ptr(desc, pdb->c_dma);
	append_ptr(desc, pdb->p_dma);
	append_ptr(desc, pdb->q_dma);
	append_ptr(desc, pdb->dp_dma);
	append_ptr(desc, pdb->dq_dma);
	append_ptr(desc, pdb->tmp1_dma);
	append_ptr(desc, pdb->tmp2_dma);
	append_cmd(desc, pdb->p_q_len);
	append_operation(desc, OP_TYPE_UNI_PROTOCOL | OP_PCLID_RSADEC_PRVKEY |
			 RSA_PRIV_KEY_FRM_3);
}