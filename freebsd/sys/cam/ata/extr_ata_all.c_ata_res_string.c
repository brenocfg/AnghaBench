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
struct sbuf {int dummy; } ;
struct ata_res {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int /*<<< orphan*/  ata_res_sbuf (struct ata_res*,struct sbuf*) ; 
 char* sbuf_data (struct sbuf*) ; 
 int sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,size_t,int /*<<< orphan*/ ) ; 

char *
ata_res_string(struct ata_res *res, char *res_string, size_t len)
{
	struct sbuf sb;
	int error;

	if (len == 0)
		return ("");

	sbuf_new(&sb, res_string, len, SBUF_FIXEDLEN);
	ata_res_sbuf(res, &sb);

	error = sbuf_finish(&sb);
	if (error != 0 && error != ENOMEM)
		return ("");

	return(sbuf_data(&sb));
}