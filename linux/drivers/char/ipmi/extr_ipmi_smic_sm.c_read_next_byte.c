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
struct si_sm_data {size_t read_pos; int truncated; int /*<<< orphan*/ * read_data; } ;

/* Variables and functions */
 size_t MAX_SMIC_READ_SIZE ; 
 int /*<<< orphan*/  read_smic_data (struct si_sm_data*) ; 

__attribute__((used)) static inline void read_next_byte(struct si_sm_data *smic)
{
	if (smic->read_pos >= MAX_SMIC_READ_SIZE) {
		read_smic_data(smic);
		smic->truncated = 1;
	} else {
		smic->read_data[smic->read_pos] = read_smic_data(smic);
		smic->read_pos++;
	}
}