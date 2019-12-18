#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_init (TYPE_1__*) ; 
 int /*<<< orphan*/  BN_FLG_MALLOCED ; 
 scalar_t__ malloc (int) ; 

BN_CTX *BN_CTX_new(void)
	{
	BN_CTX *ret;

	ret=(BN_CTX *)malloc(sizeof(BN_CTX));
	if (ret == NULL)
		{
		return(NULL);
		}

	BN_CTX_init(ret);
	ret->flags=BN_FLG_MALLOCED;
	return(ret);
	}