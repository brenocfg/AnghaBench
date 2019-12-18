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
struct thread {int dummy; } ;
struct snp_softc {int /*<<< orphan*/  snp_outwait; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SNP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devfs_set_cdevpriv (struct snp_softc*,int /*<<< orphan*/ ) ; 
 struct snp_softc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snp_dtor ; 

__attribute__((used)) static int
snp_open(struct cdev *dev, int flag, int mode, struct thread *td)
{
	struct snp_softc *ss;

	/* Allocate per-snoop data. */
	ss = malloc(sizeof(struct snp_softc), M_SNP, M_WAITOK|M_ZERO);
	cv_init(&ss->snp_outwait, "snp out");

	devfs_set_cdevpriv(ss, snp_dtor);

	return (0);
}