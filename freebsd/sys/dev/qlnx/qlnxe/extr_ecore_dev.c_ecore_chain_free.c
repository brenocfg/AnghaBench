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
struct ecore_dev {int dummy; } ;
struct ecore_chain {int mode; } ;

/* Variables and functions */
#define  ECORE_CHAIN_MODE_NEXT_PTR 130 
#define  ECORE_CHAIN_MODE_PBL 129 
#define  ECORE_CHAIN_MODE_SINGLE 128 
 int /*<<< orphan*/  ecore_chain_free_next_ptr (struct ecore_dev*,struct ecore_chain*) ; 
 int /*<<< orphan*/  ecore_chain_free_pbl (struct ecore_dev*,struct ecore_chain*) ; 
 int /*<<< orphan*/  ecore_chain_free_single (struct ecore_dev*,struct ecore_chain*) ; 

void ecore_chain_free(struct ecore_dev *p_dev,
		      struct ecore_chain *p_chain)
{
	switch (p_chain->mode) {
	case ECORE_CHAIN_MODE_NEXT_PTR:
		ecore_chain_free_next_ptr(p_dev, p_chain);
		break;
	case ECORE_CHAIN_MODE_SINGLE:
		ecore_chain_free_single(p_dev, p_chain);
		break;
	case ECORE_CHAIN_MODE_PBL:
		ecore_chain_free_pbl(p_dev, p_chain);
		break;
	}
}