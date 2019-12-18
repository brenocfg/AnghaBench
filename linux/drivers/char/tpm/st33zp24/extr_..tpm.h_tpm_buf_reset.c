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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tpm_header {void* ordinal; void* length; int /*<<< orphan*/  tag; } ;
struct tpm_buf {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static inline void tpm_buf_reset(struct tpm_buf *buf, u16 tag, u32 ordinal)
{
	struct tpm_header *head = (struct tpm_header *)buf->data;

	head->tag = cpu_to_be16(tag);
	head->length = cpu_to_be32(sizeof(*head));
	head->ordinal = cpu_to_be32(ordinal);
}