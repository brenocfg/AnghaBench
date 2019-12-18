#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int votes; } ;
typedef  TYPE_1__ PTW_tableentry ;

/* Variables and functions */
 int* eval ; 
 int n ; 

__attribute__((used)) static void getdrv(PTW_tableentry orgtable[][n], int keylen, double * normal, double * ausreiser) {
        int i,j;
	int numvotes = 0;
        double e;
	double e2;
	double emax;
        double help = 0.0;
	double maxhelp = 0;
	double maxi = 0;
        for (i = 0; i < n; i++) {
                numvotes += orgtable[0][i].votes;
        }
        e = numvotes/n;
        for (i = 0; i < keylen; i++) {
		emax = eval[i] * numvotes;
		e2 = ((1.0 - eval[i])/255.0) * numvotes;
		normal[i] = 0;
		ausreiser[i] = 0;
		maxhelp = 0;
		maxi = 0;
		for (j = 0; j < n; j++) {
			if (orgtable[i][j].votes > maxhelp) {
				maxhelp = orgtable[i][j].votes;
				maxi = j;
			}
		}
                for (j = 0; j < n; j++) {
			if (j == maxi) {
				help = (1.0-orgtable[i][j].votes/emax);
			} else {
				help = (1.0-orgtable[i][j].votes/e2);
			}
			help = help*help;
			ausreiser[i] += help;
			help = (1.0-orgtable[i][j].votes/e);
			help = help*help;
			normal[i] += help;
                }
        }
}