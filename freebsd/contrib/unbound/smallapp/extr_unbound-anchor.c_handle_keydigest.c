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
typedef  scalar_t__ time_t ;
struct xml_data {int use_key; scalar_t__ date; int /*<<< orphan*/  cdigest; int /*<<< orphan*/  cdigtype; int /*<<< orphan*/  calgo; int /*<<< orphan*/  ctag; } ;
typedef  int /*<<< orphan*/  XML_Char ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ find_att (int /*<<< orphan*/  const**,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ verb ; 
 scalar_t__ xml_convertdate (scalar_t__) ; 

__attribute__((used)) static void
handle_keydigest(struct xml_data* data, const XML_Char **atts)
{
	data->use_key = 0;
	if(find_att(atts, "validFrom")) {
		time_t from = xml_convertdate(find_att(atts, "validFrom"));
		if(from == 0) {
			if(verb) printf("error: xml cannot be parsed\n");
			exit(0);
		}
		if(data->date < from)
			return;
	}
	if(find_att(atts, "validUntil")) {
		time_t until = xml_convertdate(find_att(atts, "validUntil"));
		if(until == 0) {
			if(verb) printf("error: xml cannot be parsed\n");
			exit(0);
		}
		if(data->date > until)
			return;
	}
	/* yes we want to use this key */
	data->use_key = 1;
	(void)BIO_reset(data->ctag);
	(void)BIO_reset(data->calgo);
	(void)BIO_reset(data->cdigtype);
	(void)BIO_reset(data->cdigest);
}