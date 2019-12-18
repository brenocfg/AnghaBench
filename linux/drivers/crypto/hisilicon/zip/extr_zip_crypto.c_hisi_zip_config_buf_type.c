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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct hisi_zip_sqe {int dw9; } ;

/* Variables and functions */
 int FIELD_PREP (int,int /*<<< orphan*/ ) ; 
 int HZIP_BUF_TYPE_M ; 

__attribute__((used)) static void hisi_zip_config_buf_type(struct hisi_zip_sqe *sqe, u8 buf_type)
{
	u32 val;

	val = (sqe->dw9) & ~HZIP_BUF_TYPE_M;
	val |= FIELD_PREP(HZIP_BUF_TYPE_M, buf_type);
	sqe->dw9 = val;
}