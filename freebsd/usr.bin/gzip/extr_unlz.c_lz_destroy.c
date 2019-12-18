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
struct lz_decoder {int /*<<< orphan*/  obuf; scalar_t__ fout; scalar_t__ fin; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lz_destroy(struct lz_decoder *lz)
{
	if (lz->fin)
		fclose(lz->fin);
	if (lz->fout)
		fclose(lz->fout);
	free(lz->obuf);
}