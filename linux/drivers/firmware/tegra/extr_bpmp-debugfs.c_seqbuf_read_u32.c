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
typedef  int /*<<< orphan*/  uint32_t ;
struct seqbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int seqbuf_read (struct seqbuf*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int seqbuf_read_u32(struct seqbuf *seqbuf, uint32_t *v)
{
	int err;

	err = seqbuf_read(seqbuf, v, 4);
	*v = le32_to_cpu(*v);
	return err;
}