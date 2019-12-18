#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tcd; scalar_t__ inth; scalar_t__ errh; scalar_t__ eeih; scalar_t__ erqh; scalar_t__ errl; scalar_t__ intl; scalar_t__ cdne; scalar_t__ ssrt; scalar_t__ cerr; scalar_t__ cint; scalar_t__ ceei; scalar_t__ seei; scalar_t__ cerq; scalar_t__ serq; scalar_t__ eeil; scalar_t__ erql; scalar_t__ es; scalar_t__ cr; } ;
struct fsl_edma_engine {scalar_t__ membase; TYPE_2__ regs; TYPE_1__* drvdata; } ;
struct TYPE_3__ {scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ EDMA64_CDNE ; 
 scalar_t__ EDMA64_CEEI ; 
 scalar_t__ EDMA64_CERQ ; 
 scalar_t__ EDMA64_CERR ; 
 scalar_t__ EDMA64_CINT ; 
 scalar_t__ EDMA64_EEIH ; 
 scalar_t__ EDMA64_ERQH ; 
 scalar_t__ EDMA64_ERRH ; 
 scalar_t__ EDMA64_ERRL ; 
 scalar_t__ EDMA64_INTH ; 
 scalar_t__ EDMA64_INTL ; 
 scalar_t__ EDMA64_SEEI ; 
 scalar_t__ EDMA64_SERQ ; 
 scalar_t__ EDMA64_SSRT ; 
 scalar_t__ EDMA_CDNE ; 
 scalar_t__ EDMA_CEEI ; 
 scalar_t__ EDMA_CERQ ; 
 scalar_t__ EDMA_CERR ; 
 scalar_t__ EDMA_CINT ; 
 scalar_t__ EDMA_CR ; 
 scalar_t__ EDMA_EEI ; 
 scalar_t__ EDMA_ERQ ; 
 scalar_t__ EDMA_ERR ; 
 scalar_t__ EDMA_ES ; 
 scalar_t__ EDMA_INTR ; 
 scalar_t__ EDMA_SEEI ; 
 scalar_t__ EDMA_SERQ ; 
 scalar_t__ EDMA_SSRT ; 
 scalar_t__ EDMA_TCD ; 
 scalar_t__ v2 ; 

void fsl_edma_setup_regs(struct fsl_edma_engine *edma)
{
	edma->regs.cr = edma->membase + EDMA_CR;
	edma->regs.es = edma->membase + EDMA_ES;
	edma->regs.erql = edma->membase + EDMA_ERQ;
	edma->regs.eeil = edma->membase + EDMA_EEI;

	edma->regs.serq = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_SERQ : EDMA_SERQ);
	edma->regs.cerq = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_CERQ : EDMA_CERQ);
	edma->regs.seei = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_SEEI : EDMA_SEEI);
	edma->regs.ceei = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_CEEI : EDMA_CEEI);
	edma->regs.cint = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_CINT : EDMA_CINT);
	edma->regs.cerr = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_CERR : EDMA_CERR);
	edma->regs.ssrt = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_SSRT : EDMA_SSRT);
	edma->regs.cdne = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_CDNE : EDMA_CDNE);
	edma->regs.intl = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_INTL : EDMA_INTR);
	edma->regs.errl = edma->membase + ((edma->drvdata->version == v2) ?
			EDMA64_ERRL : EDMA_ERR);

	if (edma->drvdata->version == v2) {
		edma->regs.erqh = edma->membase + EDMA64_ERQH;
		edma->regs.eeih = edma->membase + EDMA64_EEIH;
		edma->regs.errh = edma->membase + EDMA64_ERRH;
		edma->regs.inth = edma->membase + EDMA64_INTH;
	}

	edma->regs.tcd = edma->membase + EDMA_TCD;
}