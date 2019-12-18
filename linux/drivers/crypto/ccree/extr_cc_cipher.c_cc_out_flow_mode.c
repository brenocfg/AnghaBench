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
struct cc_cipher_ctx {int flow_mode; } ;

/* Variables and functions */
 int DIN_AES_DOUT ; 
 int DIN_DES_DOUT ; 
 int DIN_SM4_DOUT ; 
#define  S_DIN_to_AES 130 
#define  S_DIN_to_DES 129 
#define  S_DIN_to_SM4 128 

__attribute__((used)) static int cc_out_flow_mode(struct cc_cipher_ctx *ctx_p)
{
	switch (ctx_p->flow_mode) {
	case S_DIN_to_AES:
		return DIN_AES_DOUT;
	case S_DIN_to_DES:
		return DIN_DES_DOUT;
	case S_DIN_to_SM4:
		return DIN_SM4_DOUT;
	default:
		return ctx_p->flow_mode;
	}
}