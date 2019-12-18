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
typedef  scalar_t__ uint16_t ;
struct pdata_ops {scalar_t__ v; } ;

/* Variables and functions */
 struct pdata_ops const* ForCES_pdata ; 
 int PD_MAX_IND ; 
 int PD_RSV_I ; 
 size_t TOM_RSV_I ; 

__attribute__((used)) static inline const struct pdata_ops *get_forces_pd(uint16_t pd)
{
	int i;
	for (i = PD_RSV_I + 1; i <= PD_MAX_IND; i++) {
		const struct pdata_ops *pdo = &ForCES_pdata[i];
		if (pdo->v == pd)
			return pdo;
	}
	return &ForCES_pdata[TOM_RSV_I];
}