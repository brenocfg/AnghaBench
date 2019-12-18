#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* m_name; char* m_mailer; int /*<<< orphan*/  m_argv; } ;
struct TYPE_3__ {char* m_name; char* m_mailer; int /*<<< orphan*/  m_argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  discardargv ; 
 TYPE_2__ discardmailer ; 
 int /*<<< orphan*/  errorargv ; 
 TYPE_1__ errormailer ; 

void
initerrmailers()
{
	if (discardmailer.m_name == NULL)
	{
		/* initialize the discard mailer */
		discardmailer.m_name = "*discard*";
		discardmailer.m_mailer = "DISCARD";
		discardmailer.m_argv = discardargv;
	}
	if (errormailer.m_name == NULL)
	{
		/* initialize the bogus mailer */
		errormailer.m_name = "*error*";
		errormailer.m_mailer = "ERROR";
		errormailer.m_argv = errorargv;
	}
}