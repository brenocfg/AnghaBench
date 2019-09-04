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
struct rerere_id {int dummy; } ;

/* Variables and functions */
 struct rerere_id* new_rerere_id_hex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha1_to_hex (unsigned char*) ; 

__attribute__((used)) static struct rerere_id *new_rerere_id(unsigned char *sha1)
{
	return new_rerere_id_hex(sha1_to_hex(sha1));
}