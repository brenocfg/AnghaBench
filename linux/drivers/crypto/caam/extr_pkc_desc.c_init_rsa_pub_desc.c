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
struct rsa_pub_pdb {int /*<<< orphan*/  f_len; int /*<<< orphan*/  e_dma; int /*<<< orphan*/  n_dma; int /*<<< orphan*/  g_dma; int /*<<< orphan*/  f_dma; int /*<<< orphan*/  sgf; } ;

/* Variables and functions */
 int OP_PCLID_RSAENC_PUBKEY ; 
 int OP_TYPE_UNI_PROTOCOL ; 
 int /*<<< orphan*/  SIZEOF_RSA_PUB_PDB ; 
 int /*<<< orphan*/  append_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_operation (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  append_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_job_desc_pdb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void init_rsa_pub_desc(u32 *desc, struct rsa_pub_pdb *pdb)
{
	init_job_desc_pdb(desc, 0, SIZEOF_RSA_PUB_PDB);
	append_cmd(desc, pdb->sgf);
	append_ptr(desc, pdb->f_dma);
	append_ptr(desc, pdb->g_dma);
	append_ptr(desc, pdb->n_dma);
	append_ptr(desc, pdb->e_dma);
	append_cmd(desc, pdb->f_len);
	append_operation(desc, OP_TYPE_UNI_PROTOCOL | OP_PCLID_RSAENC_PUBKEY);
}