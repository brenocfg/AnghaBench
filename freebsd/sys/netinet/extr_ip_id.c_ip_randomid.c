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
typedef  int /*<<< orphan*/  new_id ;

/* Variables and functions */
 size_t V_array_ptr ; 
 size_t V_array_size ; 
 scalar_t__* V_id_array ; 
 int /*<<< orphan*/  V_id_bits ; 
 int /*<<< orphan*/  V_ip_id_mtx ; 
 int /*<<< orphan*/  V_random_id_collisions ; 
 int /*<<< orphan*/  V_random_id_total ; 
 int /*<<< orphan*/  arc4rand (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bit_clear (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bit_test (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint16_t
ip_randomid(void)
{
	uint16_t new_id;

	mtx_lock(&V_ip_id_mtx);
	/*
	 * To avoid a conflict with the zeros that the array is initially
	 * filled with, we never hand out an id of zero.
	 */
	new_id = 0;
	do {
		if (new_id != 0)
			V_random_id_collisions++;
		arc4rand(&new_id, sizeof(new_id), 0);
	} while (bit_test(V_id_bits, new_id) || new_id == 0);
	bit_clear(V_id_bits, V_id_array[V_array_ptr]);
	bit_set(V_id_bits, new_id);
	V_id_array[V_array_ptr] = new_id;
	V_array_ptr++;
	if (V_array_ptr == V_array_size)
		V_array_ptr = 0;
	V_random_id_total++;
	mtx_unlock(&V_ip_id_mtx);
	return (new_id);
}