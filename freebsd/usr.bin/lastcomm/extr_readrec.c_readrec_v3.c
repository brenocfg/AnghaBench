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
struct acctv3 {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fread_record (struct acctv3*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
readrec_v3(FILE *f, struct acctv3 *av3)
{

	return (fread_record(av3, sizeof(*av3), f));
}