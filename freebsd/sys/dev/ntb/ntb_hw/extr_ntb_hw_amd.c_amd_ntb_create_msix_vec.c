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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct amd_ntb_softc {TYPE_1__* msix_vec; } ;
struct TYPE_2__ {int num; struct amd_ntb_softc* ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AMD_NTB ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
amd_ntb_create_msix_vec(struct amd_ntb_softc *ntb, uint32_t max_vectors)
{
	uint8_t i;
	
	ntb->msix_vec = malloc(max_vectors * sizeof(*ntb->msix_vec), M_AMD_NTB,
	    M_ZERO | M_WAITOK);

	for (i = 0; i < max_vectors; i++) {
		ntb->msix_vec[i].num = i;
		ntb->msix_vec[i].ntb = ntb;
	}

	return (0);
}