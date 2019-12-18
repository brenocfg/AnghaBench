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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sae_data {TYPE_1__* tmp; } ;
struct TYPE_2__ {scalar_t__ dh; } ;

/* Variables and functions */
 int /*<<< orphan*/  sae_parse_commit_element_ecc (struct sae_data*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sae_parse_commit_element_ffc (struct sae_data*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static u16 sae_parse_commit_element(struct sae_data *sae, const u8 **pos,
				    const u8 *end)
{
	if (sae->tmp->dh)
		return sae_parse_commit_element_ffc(sae, pos, end);
	return sae_parse_commit_element_ecc(sae, pos, end);
}