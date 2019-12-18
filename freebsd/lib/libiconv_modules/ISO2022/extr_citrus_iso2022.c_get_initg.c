#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* initg; } ;
typedef  TYPE_2__ _ISO2022EncodingInfo ;
struct TYPE_8__ {int /*<<< orphan*/  vers; int /*<<< orphan*/  interm; int /*<<< orphan*/  final; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ _ISO2022Charset ;
struct TYPE_6__ {int /*<<< orphan*/  vers; int /*<<< orphan*/  interm; int /*<<< orphan*/  final; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int _MATCH ; 
 int _NOTMATCH ; 
 int _PARSEFAIL ; 
 scalar_t__ getcs (char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  strchr (char*,char const) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static __inline int
get_initg(_ISO2022EncodingInfo * __restrict ei,
    const char * __restrict token)
{
	_ISO2022Charset cs;

	if (strncmp("INIT", &token[0], 4) ||
	    !strchr("0123", token[4]) ||
	    token[5] != '=')
		return (_NOTMATCH);

	if (getcs(&token[6], &cs) != 0)
		return (_PARSEFAIL);

	ei->initg[token[4] - '0'].type = cs.type;
	ei->initg[token[4] - '0'].final = cs.final;
	ei->initg[token[4] - '0'].interm = cs.interm;
	ei->initg[token[4] - '0'].vers = cs.vers;

	return (_MATCH);
}