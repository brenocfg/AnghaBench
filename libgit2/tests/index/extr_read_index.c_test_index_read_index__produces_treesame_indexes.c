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

/* Variables and functions */
 int /*<<< orphan*/  roundtrip_with_read_index (char*) ; 

void test_index_read_index__produces_treesame_indexes(void)
{
	roundtrip_with_read_index("53fc32d17276939fc79ed05badaef2db09990016");
	roundtrip_with_read_index("944c0f6e4dfa41595e6eb3ceecdb14f50fe18162");
	roundtrip_with_read_index("1810dff58d8a660512d4832e740f692884338ccd");
	roundtrip_with_read_index("d52a8fe84ceedf260afe4f0287bbfca04a117e83");
	roundtrip_with_read_index("c36d8ea75da8cb510fcb0c408c1d7e53f9a99dbe");
	roundtrip_with_read_index("7b2417a23b63e1fdde88c80e14b33247c6e5785a");
	roundtrip_with_read_index("f82a8eb4cb20e88d1030fd10d89286215a715396");
	roundtrip_with_read_index("fd093bff70906175335656e6ce6ae05783708765");
	roundtrip_with_read_index("ae90f12eea699729ed24555e40b9fd669da12a12");
}