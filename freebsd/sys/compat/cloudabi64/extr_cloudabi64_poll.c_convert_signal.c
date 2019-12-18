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
typedef  scalar_t__ cloudabi_signal_t ;

/* Variables and functions */
#define  CLOUDABI_SIGABRT 179 
#define  CLOUDABI_SIGALRM 178 
#define  CLOUDABI_SIGBUS 177 
#define  CLOUDABI_SIGCHLD 176 
#define  CLOUDABI_SIGCONT 175 
#define  CLOUDABI_SIGFPE 174 
#define  CLOUDABI_SIGHUP 173 
#define  CLOUDABI_SIGILL 172 
#define  CLOUDABI_SIGINT 171 
#define  CLOUDABI_SIGKILL 170 
#define  CLOUDABI_SIGPIPE 169 
#define  CLOUDABI_SIGQUIT 168 
#define  CLOUDABI_SIGSEGV 167 
#define  CLOUDABI_SIGSTOP 166 
#define  CLOUDABI_SIGSYS 165 
#define  CLOUDABI_SIGTERM 164 
#define  CLOUDABI_SIGTRAP 163 
#define  CLOUDABI_SIGTSTP 162 
#define  CLOUDABI_SIGTTIN 161 
#define  CLOUDABI_SIGTTOU 160 
#define  CLOUDABI_SIGURG 159 
#define  CLOUDABI_SIGUSR1 158 
#define  CLOUDABI_SIGUSR2 157 
#define  CLOUDABI_SIGVTALRM 156 
#define  CLOUDABI_SIGXCPU 155 
#define  CLOUDABI_SIGXFSZ 154 
#define  SIGABRT 153 
#define  SIGALRM 152 
#define  SIGBUS 151 
#define  SIGCHLD 150 
#define  SIGCONT 149 
#define  SIGFPE 148 
#define  SIGHUP 147 
#define  SIGILL 146 
#define  SIGINT 145 
#define  SIGKILL 144 
#define  SIGPIPE 143 
#define  SIGQUIT 142 
#define  SIGSEGV 141 
#define  SIGSTOP 140 
#define  SIGSYS 139 
#define  SIGTERM 138 
#define  SIGTRAP 137 
#define  SIGTSTP 136 
#define  SIGTTIN 135 
#define  SIGTTOU 134 
#define  SIGURG 133 
#define  SIGUSR1 132 
#define  SIGUSR2 131 
#define  SIGVTALRM 130 
#define  SIGXCPU 129 
#define  SIGXFSZ 128 
 int nitems (scalar_t__ const*) ; 

__attribute__((used)) static cloudabi_signal_t
convert_signal(int sig)
{
	static const cloudabi_signal_t signals[] = {
		[SIGABRT]	= CLOUDABI_SIGABRT,
		[SIGALRM]	= CLOUDABI_SIGALRM,
		[SIGBUS]	= CLOUDABI_SIGBUS,
		[SIGCHLD]	= CLOUDABI_SIGCHLD,
		[SIGCONT]	= CLOUDABI_SIGCONT,
		[SIGFPE]	= CLOUDABI_SIGFPE,
		[SIGHUP]	= CLOUDABI_SIGHUP,
		[SIGILL]	= CLOUDABI_SIGILL,
		[SIGINT]	= CLOUDABI_SIGINT,
		[SIGKILL]	= CLOUDABI_SIGKILL,
		[SIGPIPE]	= CLOUDABI_SIGPIPE,
		[SIGQUIT]	= CLOUDABI_SIGQUIT,
		[SIGSEGV]	= CLOUDABI_SIGSEGV,
		[SIGSTOP]	= CLOUDABI_SIGSTOP,
		[SIGSYS]	= CLOUDABI_SIGSYS,
		[SIGTERM]	= CLOUDABI_SIGTERM,
		[SIGTRAP]	= CLOUDABI_SIGTRAP,
		[SIGTSTP]	= CLOUDABI_SIGTSTP,
		[SIGTTIN]	= CLOUDABI_SIGTTIN,
		[SIGTTOU]	= CLOUDABI_SIGTTOU,
		[SIGURG]	= CLOUDABI_SIGURG,
		[SIGUSR1]	= CLOUDABI_SIGUSR1,
		[SIGUSR2]	= CLOUDABI_SIGUSR2,
		[SIGVTALRM]	= CLOUDABI_SIGVTALRM,
		[SIGXCPU]	= CLOUDABI_SIGXCPU,
		[SIGXFSZ]	= CLOUDABI_SIGXFSZ,
	};

	/* Convert unknown signals to SIGABRT. */
	if (sig < 0 || sig >= nitems(signals) || signals[sig] == 0)
		return (SIGABRT);
	return (signals[sig]);
}