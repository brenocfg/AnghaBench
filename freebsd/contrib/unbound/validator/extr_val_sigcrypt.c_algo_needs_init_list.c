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
typedef  size_t uint8_t ;
struct algo_needs {int* needs; size_t num; } ;

/* Variables and functions */
 int ALGO_NEEDS_MAX ; 
 int dnskey_algo_id_is_supported (int) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void algo_needs_init_list(struct algo_needs* n, uint8_t* sigalg)
{
	uint8_t algo;
	size_t total = 0;

	memset(n->needs, 0, sizeof(uint8_t)*ALGO_NEEDS_MAX);
	while( (algo=*sigalg++) != 0) {
		log_assert(dnskey_algo_id_is_supported((int)algo));
		log_assert(n->needs[algo] == 0);
		n->needs[algo] = 1;
		total++;
	}
	n->num = total;
}