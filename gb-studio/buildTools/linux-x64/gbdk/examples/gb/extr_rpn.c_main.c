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
typedef  int WORD ;
typedef  int BYTE ;

/* Variables and functions */
#define  NUMBER 128 
 int n ; 
 int pop () ; 
 scalar_t__ pos ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  push (int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int read_op () ; 
 scalar_t__ sp ; 
 int top () ; 

void main(void)
{
  BYTE type;
  WORD op2;

  puts("RPN Calculator");
  sp = 0;
  pos = 0;

  while((type = read_op()) != 0) {
    switch(type) {
    case NUMBER:
      push(n);
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if(op2 != 0)
	push(pop() / op2);
      else
	puts("Divide by 0");
      break;
    case '\n':
      printf("==> %d\n", top());
      break;
    }
  }
}