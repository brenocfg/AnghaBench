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
typedef  int /*<<< orphan*/  u32 ;
struct img_hash_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_RESULT_QUEUE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_hash_read (struct img_hash_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 img_hash_read_result_queue(struct img_hash_dev *hdev)
{
	return be32_to_cpu(img_hash_read(hdev, CR_RESULT_QUEUE));
}