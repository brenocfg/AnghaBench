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
struct url_stat {int dummy; } ;
struct url {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * http_request_body (struct url*,char const*,struct url_stat*,struct url*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

FILE *
http_request(struct url *URL, const char *op, struct url_stat *us,
	struct url *purl, const char *flags)
{

	return (http_request_body(URL, op, us, purl, flags, NULL, NULL));
}