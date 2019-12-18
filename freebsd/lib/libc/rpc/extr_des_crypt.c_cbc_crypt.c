#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* UDES_buf; } ;
struct desparams {char* des_ivec; int /*<<< orphan*/  des_mode; TYPE_1__ UDES; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBC ; 
 int /*<<< orphan*/  COPY8 (char*,char*) ; 
 int /*<<< orphan*/  ECB ; 
 int common_crypt (char*,char*,unsigned int,unsigned int,struct desparams*) ; 

int
cbc_crypt(char *key, char *buf, unsigned len, unsigned mode, char *ivec)
{
	int err;
	struct desparams dp;

#ifdef BROKEN_DES
	dp.UDES.UDES_buf = buf;
	dp.des_mode = ECB;
#else
	dp.des_mode = CBC;
#endif
	COPY8(ivec, dp.des_ivec);
	err = common_crypt(key, buf, len, mode, &dp);
	COPY8(dp.des_ivec, ivec);
	return(err);
}