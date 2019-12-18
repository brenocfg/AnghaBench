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
typedef  int /*<<< orphan*/  u16 ;
struct tpm_header {int /*<<< orphan*/  tag; } ;
struct tpm_buf {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 tpm_buf_tag(struct tpm_buf *buf)
{
	struct tpm_header *head = (struct tpm_header *)buf->data;

	return be16_to_cpu(head->tag);
}